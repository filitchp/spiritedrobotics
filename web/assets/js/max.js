$(function(){
    MaxFrames = Backbone.View.extend(
    {
        tagName:'img',
        collection:AllFrames,
        initialize: function()
        {
            var self = this;
            this.collection.on(
            {
                "sync":function{ self.render() }
            });
        },
        render: function(){
            this.colletion.each(function(frame, i)
            {
                $("#preload").append("<img src=\"" + frame.get("imagePath") + "\" width=\"1\" height=\"1\"/>");
            }
        }
    });
});
