$(function()
{
    //------------------------------------
    // This model describes a single order
    //------------------------------------
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
            'click .click-to-test' : 'test'
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
        render: function(){
            var template = _.template($("#debug_template").html());
            this.$el.html(template());
            $("#debug-container").append(this.$el);
            return this;
        }
    });

});
