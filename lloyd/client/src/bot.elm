module Bot exposing (BotState, decoder, endpoint) where
  
import Json.Decoder as Decode

endpoint = "spiritedrobotics-lloyd.herokuapp.com"
endpoint = "127.0.0.1:8080"    

type alias BotState = {
   name : String,
   drink : String,
   status : String,
   nonce : Int
}

decoder = Decode.object4 BotState
       ("name"   := Decode.string)
       ("drink"  := Decode.string)
       ("status" := Decode.string)
       ("nonce"  := Decode.int)   


fetchNewState : Task Http.Error BotState
fetchNewState = Http.get decoder ("http://" ++ botstateEndpoint)
