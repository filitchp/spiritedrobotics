$(function()
{
    //-------------------------------------
    // This model describes a single drink
    //-------------------------------------
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
    
    //--------------------------------------------------------
    // This is a collection of drinks fetched from the server
    //--------------------------------------------------------
    Drinks = Backbone.Collection.extend(
    {
        model: Drink,
        category_key: "NIL",
        url: "assets/json/drinks.json",
        data: { category: this.category_key }
    });
    
    AllDrinks = Backbone.Collection.extend(
    {
        model: Drink,
        url:"assets/json/drinks.json"
    });
 
});
