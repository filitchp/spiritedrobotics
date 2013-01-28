$(function()
{
    Drink = Backbone.Model.extend(
    {
        defaults: {
            name: "Not Specified",
            description: "Not Specified",
            key: "NIL",
            ingredients: "NIL",
            imagePath: "NIL"
        },
        initialize: function(){
            console.log('initialized drink: ' + this.get("name"));
        }
    });

    AllDrinks = Backbone.collection.extend(
    {
        model: Drink,
        url:"assets/json/drinks.json"
    });

});
