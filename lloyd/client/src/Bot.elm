module Bot exposing (BotState, decoder, endpoint, fetch)

import Json.Decode as Decode exposing ((:=))
import Http exposing (get)
import Task exposing (Task)

endpoint = "spiritedrobotics-lloyd.herokuapp.com"
--endpoint = "127.0.0.1:8080"    

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


fetch : Task Http.Error BotState
fetch = Http.get decoder ("http://" ++ endpoint)
