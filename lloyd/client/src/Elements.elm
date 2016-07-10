module Elements exposing (css, meta, blinkenText, scrollinText, spinninText, videoElement)


import Window exposing (Size)
import Html exposing (div, node, text, video, Attribute, Html, h1, h2)
import Html.App as App
import Html.Attributes exposing (src, autoplay, loop, property, class, style, name, content, rel, poster)
import Video exposing (VideoModel)

videoElement : VideoModel -> Html msg
videoElement vid = video [
                        class "lloyd",
                          src vid.mp4,
                          autoplay True,
                          loop True,
                          style fullonVideoStyle,
                          poster vid.gif
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
   ("transform", "translateX(-50%) translateY(-50%)") ]
  
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
   ("position", "absolute") ]
  
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
   ("top", "0") ]

spinninText : Size -> Int -> String -> Html msg
spinninText window offset message =
  let slow = (offset // 7) in
  h1 [ style <| [("transform", ""
                    ++ " translateX(" ++ (toString ((abs (((slow * 3) % window.width * 2) - window.width)) - window.width // 2 )) ++
                    "px)"
                    ++ " translateY(" ++ (toString ((abs (((slow * 5) % window.height * 2) - window.height)) - window.height // 2 ))
                    ++ "px)"
                    ++ " translateZ(" ++ (toString <| (abs ((offset % window.width) - window.width // 2)) - window.width // 4 ) ++
                    "px)"
                    ++ " rotateY("    ++ (toString ((abs (((slow * 3) % 340 ) - 170)) - 85)) ++ "deg)"
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
                                                                                                                                                   
                                                                                                                                                   *::-webkit-media-controls-panel {                                                                                                      
                                                                                                                                                   display: none!important;                                                                                                             
                                                                                                                                                   -webkit-appearance: none;                                                                                                            
                                                                                                                                                   }                                                                                                                                      
                                                                                                                                                   
                                                                                                                                                   /* Old shadow dom for play button */                                                                                                   
                                                                                                                                                   
                                                                                                                                                   *::--webkit-media-controls-play-button {                                                                                               
                                                                                                                                                   display: none!important;                                                                                                             
                                                                                                                                                   -webkit-appearance: none;                                                                                                            
                                                                                                                                                   }                                                                                                                                      
                                                                                                                                                   
                                                                                                                                                   /* New shadow dom for play button */                                                                                                   
                                                                                                                                       
/* This one works */                                                                                                                   
                                                                                                                                       
*::-webkit-media-controls-start-playback-button {                                                                                      
  display: none!important;                                                                                                             
  -webkit-appearance: none;                                                                                                            
}                                                                                                                                      
")]

meta = node "meta" [ name "viewport", content "width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no, width=400" ] []
