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
        category_title: "All",
        url:"assets/json/drinks.json"
    });
    
    //--------------------------------------------------------
    // This view renders a single drink
    //--------------------------------------------------------
    DrinkView = Backbone.View.extend(
    {
        tagName: 'div',
        model: Drink,
        template: function(){ 
            return _.template($("#drink_template").html()); 
        },
        events: {
            'click .click-to-order' : 'order'
        },
        order: function() { alert("order: " + this.model.get("key") ); },
        render: function(){
            console.log("Making " + this.model.get("key"));
            $("#drinks-list").append("<li><a href=\"#" + this.model.get("key") + "\">" + this.model.get("name") + "</a></li>");
            var ingredients = this.model.get("ingredients");
            var ingredientHtml = '';
            var ingredientTemplate = _.template($("#ingredient_template").html());
            var drinkTemplate = _.template($("#drink_template").html()); 
            $.each(ingredients, function (i,ingr)
            {
                var ingrVars = 
                {
                    name: ingr.name,
                    amount: ingr.amount
                };

                ingredientHtml = ingredientHtml + ingredientTemplate(ingrVars);
            });

            //TODO remodel this to use the drink object straight aways
            var drinkVars = 
            {
                key: this.model.get("key"),
                name: this.model.get("name"),
                description: this.model.get("description"),
                imagePath: this.model.get("imagePath"),
                ingredients: ingredientHtml
            }

            var drinkTemplatePopulated = drinkTemplate(drinkVars);
            this.$el.html(drinkTemplatePopulated);
            $("#content").append(this.$el);
            return this;
        }
    });

 
});
