import AnimationFrame exposing (diffs)
import Html exposing (div, node, text, video, Attribute, Html, h1, h2)
import Html.App as App
import Html.Attributes exposing (src, autoplay, loop, property, class, style, name, content, rel, poster)
import Http exposing (get)
import Json.Encode exposing (float, string)
import Json.Decode as Decode exposing ((:=))
import Platform.Sub exposing (batch)
import Task exposing (perform, Task)
import Time exposing (every, second, Time)
import WebSocket exposing (listen)
import Window exposing (Size, resizes, size)

--botstateEndpoint = "spiritedrobotics-lloyd.herokuapp.com"
botstateEndpoint = "127.0.0.1:8080"
(<$>) = List.map
 
type Msg =  Tick Time | Anim Time | Resize Size | Update BotState | NoOp
type Beat =  Upbeat | Downbeat
          
type alias Model = {
  beat : Beat,
  botstate : BotState,
  textPosition : Float,
  window  : Size
}

type alias BotState =  {
  name : String,
  message : String,
  status : String
}

botStateDecoder = Decode.object3 BotState ("name" := Decode.string) ("message" := Decode.string) ("status" := Decode.string)
 
main = App.program {
           init = init,
           view = view,
           update = update,
           subscriptions = subscriptions
         }

init = ({ beat = Upbeat,
          botstate = {
            name = "SantaBarbot",
            message = "DRINK SPEND DRINK SPEND DRINK",
            status = "IDLE"
          },
          textPosition = 0,
          window = {width = 400, height = 400} } , Cmd.batch [
             perform (\x -> Resize { width = 400, height = 400 }) (\i -> Resize i) size,
             perform (\x -> NoOp) (\i -> Update i) fetchNewState ])
       
view model =
  div [style [("height", "100%"), ("top", "0px"), ("overflow", "hidden") ]] ([
    meta,
    css model.window,
    blinkenText (model.beat == Upbeat) ("Order Up: " ++ model.botstate.name),
    getVideo model.botstate.status,
    scrollinText model.window (floor model.textPosition) model.botstate.message
  ] ++ if (model.botstate.status == "WARMUP") then
         [spinninText model.window (floor model.textPosition) ("THE WHEEL OF FATE IS TURNING")]
       else [])

update msg model =
  case msg of
    Tick time ->   (switchBeat model, Cmd.none)
    Anim time -> (progressTime model time, Cmd.none)
    Resize new_window -> ( {model | window = new_window}, Cmd.none)
    Update state -> ({ model | botstate = state, textPosition = 0 }, Cmd.none)
    NoOp -> (model, Cmd.none)

subscriptions model =
  batch [ every (second / 3) Tick,
          diffs (\t -> Anim t),
          resizes Resize,
          listen ("ws://" ++ botstateEndpoint) botDecoder ]

botDecoder : String -> Msg
botDecoder s = Maybe.withDefault NoOp
             <| Maybe.map Update
             <| Result.toMaybe (Decode.decodeString (botStateDecoder) s)

fetchNewState : Task Http.Error BotState
fetchNewState = Http.get botStateDecoder ("http://" ++ botstateEndpoint)
                
diffTagger : Time -> Msg
diffTagger t = Anim t
                               
switchBeat : Model -> Model
switchBeat model =
  case model.beat of
     Upbeat   -> { model | beat = Downbeat }
     Downbeat -> { model | beat = Upbeat   }
                                      
getVideo activity =
  case activity of
    "IDLE"   -> sillyExampleVideo
    "WARMUP" -> secondExampleVideo
    "MAKING" -> makingVideo
    _ -> sillyExampleVideo

progressTime : Model -> Time -> Model
progressTime model time =
  { model | textPosition = (model.textPosition + (time / 1000) * 200) }
                       
sillyExampleVideo : Html msg
sillyExampleVideo = decorateVideoUrl "static/giant_cat-compressed.mp4" "static/giant_cat.gif"
  
secondExampleVideo : Html msg
secondExampleVideo = decorateVideoUrl "static/botbattle.mp4" "static/botbattle.gif"

makingVideo : Html msg
makingVideo = decorateVideoUrl "static/lloyd_mixing-compressed.mp4" "static/lloyd_mixing.gif"
  
                     
decorateVideoUrl : String -> String -> Html msg
decorateVideoUrl url post = video [
                     class "lloyd",
                     src url,
                     autoplay True,
                     loop True,
                     style fullonVideoStyle,
                     poster post
                    ] []
  
fullonVideoStyle = [
     ("display", "block"),
     ("position", "absolute"),
     ("min-width", "100%"),
     ("min-height", "100%"),
     ("left", "50%"),
     ("top", "50%"),
     ("height", "auto"),
     ("width", "auto"),
     ("overflow", "hidden"),
     ("z-index", "-1000"),
     ("-webkit-transform", "translateX(-50%) translateY(-50%)"),
     ("transform", "translateX(-50%) translateY(-50%)")
                   ]

blinkenText : Bool -> String -> Html msg
blinkenText on message =
  case on of
    True  -> h1 [style ([("color","red"  )] ++ baseBlinkenStyle)] [text message]
    False -> h1 [style ([("color","green")] ++ baseBlinkenStyle)] [text message]

baseBlinkenStyle = [
   ("background", "black"),
   ("textAlign", "center"),
   ("overflow", "hidden"),
   ("width", "100%"),
   ("display", "inline"),
   ("position", "absolute")
 ]

scrollinText : Size -> Int -> String -> Html msg
scrollinText window offset message =
  let pos = offset % window.width in
  div [style [("position", "relative"), ("height", "200px"), ("top", "90%"), ("background", "black"), ("overflow", "hidden")]] [
     h2 [style (baseScrollinStyle ++ [("margin-left", (toString pos) ++ "px")])] [text message],
     h2 [style (baseScrollinStyle ++ [("margin-left", (toString <| pos - window.width) ++ "px")])] [text message]
        ]

baseScrollinStyle = [
   ("padding", "0 0 0 0"),
   ("margin", "0 0 0 0"),
   ("color", "blue"),
   ("position", "absolute"),
   ("display", "inline"),
   ("min-width", "400px"),
   ("width", "100%"),
   ("overflow", "hidden"),
   ("white-space", "wrap"),
   ("left", "0"),
   ("top", "0")
 ]

spinninText : Size -> Int -> String -> Html msg
spinninText window offset message =
    let slow = (offset // 3) in
    h1 [ style <| [("transform", ""
                   ++ " translateX(" ++ (toString ((abs (((slow * 3) % window.width * 2) - window.width)) - window.width // 2 )) ++ "px)"
                   ++ " translateY(" ++ (toString ((abs (((slow * 5) % window.height * 2) - window.height)) - window.height // 2 )) ++ "px)"
                   ++ " translateZ(" ++ (toString <| (abs ((offset % window.width) - window.width // 2)) - window.width // 4 ) ++ "px)"
                   ++ " rotateY("    ++ (toString <| (offset // 3) % 360) ++ "deg)"
               )] ++ baseSpinninStyle ] [text message]
       
baseSpinninStyle = [
   ("top", "40%"),
   ("padding", "0 0 0 0"),
   ("margin", "0 0 0 0"),
   ("color", "white"),
   ("position", "absolute"),
   ("display", "inline"),
   ("min-width", "400px"),
   ("textAlign", "center"),
   ("transform-style", "preserve-3d"),
   ("text-shadow", "0 0 20px black"), 
   ("width", "100%"),
   ("overflow", "hidden"),
   ("white-space", "wrap")
 ]



--Elm Clearfix...
css window = node "style" [] [text ("
  html, head, body {overflow: hidden; height: 100%; margin: 0; perspective: " ++ (window.width |> toString) ++ "px;}
")]

meta = node "meta" [ name "viewport", content "width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no, width=400" ] []
