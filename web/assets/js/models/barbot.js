$(function()
{
    //----------------------------------------
    // This model describes the BarBot system
    //----------------------------------------
    Barbot = Backbone.Model.extend(
    {
        defaults: {
            //??????
        },
        initialize: function(){
            console.log('initialized barbot: ' + '??????');
        }
    });

    DebugView = Backbone.View.extend(
    {
        tagName: 'div',
        model: Barbot,
        events: {
            'click .click-to-test' : 'test',
            'click .click-to-init' : 'init',
            'click .click-to-stop' : 'stop'
        },
        test: function(){
            $.ajax({
                type: "GET",
                url: "testTower",
                data: {
                    tower: $("#test_number").val(),
                    amount: $("#test_amount").val()
                },
                success: function(res){
                    if (res.result == true){
                      console.log(res.toString());
                    }else{
                        alert("ERR");
                    }
                }
            });
        },
     	  stop: function(){
            $.ajax({
                type: "GET",
                url: "haltTowers",
                success: function(res){
                    if (res.result == true){
                      console.log(res.toString());
                    }else{
                        alert("ERR");
                    }
                }
            });
        },
        init: function(){
             $.ajax({
                type: "GET",
                url: "initTowers",
                success: function(res){
                    if (res.result == true){
                        console.log(res.toString());
                    }else{
                        alert("ERR");
                    }
                }
            });
        },
        render: function(){
            var template = _.template($("#debug_template").html());
            this.$el.html(template());
            $("#debug-container").append(this.$el);
            return this;
        }
    });

});
