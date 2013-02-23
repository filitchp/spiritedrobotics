$(function()
{
    //------------------------------------
    // This model describes a single order
    //------------------------------------
    Order = Backbone.Model.extend(
    {
        defaults: {
            name: "Pat Doe",
            drinkKey: "NIL",
            imagePath: "NIL",
            timestamp: new Date.getTime()
        },
        initialize: function(){
            console.log('initialized order: ' + this.get("name"));
        }
    });

    //------------------------------------
    // This is a collection of orders
    //------------------------------------
    AllOrders = Backbone.Collection.extend(
    {
        model: Order,
        url:"assets/jsons/orders.json"
    });

);
    
