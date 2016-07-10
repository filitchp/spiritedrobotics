import AnimationFrame exposing (diffs)
import Hash
import Html exposing (div, node, text, video, Attribute, Html, h1, h2)
import Html.App as App
import Html.Attributes exposing (src, autoplay, loop, property, class, style, name, content, rel, poster)
import Json.Encode exposing (float, string)
import Json.Decode as Decode exposing ((:=))
import String exposing (contains)
import Platform.Sub exposing (batch)
import Task exposing (perform, Task)
import Time exposing (every, second, Time)
import WebSocket exposing (listen)
import Window exposing (Size, resizes, size)

import Bot as Bot exposing (BotState)
import Video exposing (VideoModel)
import Elements exposing (blinkenText, scrollinText, spinninText)
import Quips exposing (quips)

type Msg =  Tick Time | Anim Time | Resize Size | Update BotState | NoOp
type Beat =  Upbeat | Downbeat
          
type alias Model = {
  beat : Beat,
  botstate : BotState,
  textPosition : Float,
  window  : Size
}

main = App.program {
           init = init,
           view = view,
           update = update,
           subscriptions = subscriptions
         }

init = ({ beat = Upbeat,
          botstate = {
            name = "SantaBarbot",
            drink = "GINANDTONIC",
            status = "IDLE",
            nonce = 0
          },
          textPosition = 0,
          window = {width = 400, height = 400} } , Cmd.batch [
             perform (\x -> Resize { width = 400, height = 400 }) (\i -> Resize i) size,
             perform (\x -> NoOp) (\i -> Update i) Bot.fetch])

view : Model -> Html msg
view model =
  div [style [("height", "100%"), ("top", "0px"), ("overflow", "hidden") ]] ([
    Elements.meta,
    Elements.css model.window,
    blinkenText (model.beat == Upbeat) ("Order Up: " ++ model.botstate.name),
    getVideo model.botstate,
    scrollinText model.window (floor model.textPosition) (getQuip model.botstate)
  ] ++ if (model.botstate.status == "WARMUP") then
            [spinninText model.window (floor model.textPosition)        ("THE WHEEL OF FATE IS TURNING")]
         ++ [spinninText model.window (floor model.textPosition + 1337) ("WHAT HAS BEEN WROUGHT CAN NOT BE UNDONE")]
       else [])

update : Msg -> Model -> (Model, Cmd a)
update msg model =
  case msg of
    Tick time ->   (switchBeat model, Cmd.none)
    Anim time -> (progressTime model time, Cmd.none)
    Resize new_window -> ( {model | window = new_window}, Cmd.none)
    Update state -> ({ model | botstate = state, textPosition = 0 }, Cmd.none)
    NoOp -> (model, Cmd.none)

subscriptions : Model -> Sub Msg
subscriptions model =
  batch [ every (second / 3) Tick,
          diffs (\t -> Anim t),
          resizes Resize,
          listen ("ws://" ++ Bot.endpoint) botDecoder ]

botDecoder : String -> Msg
botDecoder s = Maybe.withDefault NoOp
             <| Maybe.map Update
             <| Result.toMaybe (Decode.decodeString (Bot.decoder) s)

diffTagger : Time -> Msg
diffTagger t = Anim t
                               
switchBeat : Model -> Model
switchBeat model =
  case model.beat of
     Upbeat   -> { model | beat = Downbeat }
     Downbeat -> { model | beat = Upbeat   }

getVideo : BotState -> Html msg                 
getVideo botState =
  let matchingStatus = List.filter (\v -> v.status == botState.status) in
    case botState.status == "WARMUP" && contains "PANGALACTIC" botState.drink of
    True -> Elements.videoElement <| Video.construct "pangalactic" "WARMUP"
    _ -> Elements.videoElement <| Maybe.withDefault fallbackVideo <| rotated (botState.nonce) ( matchingStatus Video.videos )

getQuip : BotState -> String
getQuip botState = Maybe.withDefault "DRINK SPEND DRINK SPEND DRINK" <| rotated ((Hash.hash botState.name) % List.length quips) quips
         
rotated : Int -> List a -> Maybe a
rotated i list = List.head <| List.drop (i % (List.length list)) list
     
progressTime : Model -> Time -> Model
progressTime model time =
  { model | textPosition = (model.textPosition + (time / 1000) * 200) }

fallbackVideo : VideoModel
fallbackVideo = { gif = "", mp4 = "", status = "" }
