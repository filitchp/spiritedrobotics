module Video exposing (VideoModel, construct, videos)

import Bot exposing (BotState)

type alias VideoModel = {
    gif : String,
    mp4 : String,
    status : String
}

construct : String -> String -> VideoModel
construct name show_status =
  { gif = "static/" ++ name ++ ".gif",
    mp4 = "static/" ++ name ++ "-compressed.mp4",
    status = show_status }

videos : List VideoModel    
videos = [
  construct "botbattle"      "WARMUP"
 ,construct "giant_cat"      "IDLE"
 ,construct "lloyd_chatter"  "IDLE"
 ,construct "lloyd_mixing"   "POURING"
 ,construct "shining_boot"   "WARMUP"
 ,construct "shining_boot2"  "WARMUP"
 ,construct "max"            "IDLE"
 ,construct "irobo"          "WARMUP"
 ,construct "data"           "IDLE"
 ,construct "ironman"        "WARMUP"
 ,construct "tinkles"        "WARMUP"
 ,construct "trump"          "WARMUP"
 ,construct "whatllitbe"     "IDLE" ]  
