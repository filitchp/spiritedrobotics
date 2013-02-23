$(function() 
{
  
  drinks = new AllDrinks();
  categories = new ValidCategories();

  //-------------------------------
  // This draws the menu of drinks
  //-------------------------------  
  DrinkView = Backbone.View.extend(
  {
    tagName: 'li',
    collection: drinks,
    initialize: function()
    {
      var self = this;
      this.collection.on({
          "sync": function(){ self.render() }
      });
    },
    render: function()
    {
      
      // Compile the drink template using underscore
      var drinkTemplate = _.template($("#drink_template").html());
      
      //Compile the ingredient template using underscore
      var ingredientTemplate = _.template($("#ingredient_template").html());
      
      // Clear the menu
      $("#drinks-list").empty();
      
      $(".category_title").html(this.collection.category_title);

      // For each drink
      this.collection.each(function(drink)
      {
        $("#drinks-list").append("<li><a href=\"#" + drink.get("key") + "\">" + drink.get("name") + "</a></li>");
        
        // Get the ingredients for this drink
        var ingredients = drink.get("ingredients");
        
        var ingredientHtml = '';

        // For each ingredient
        $.each(ingredients, function(i, ingr)
        {
          // Ingredient template variables
          var ingrVars =
          {
            name: ingr.name,
            amount: ingr.amount
          };
          
          // Populate the ingredient template and append
          ingredientHtml = ingredientHtml + ingredientTemplate(ingrVars);
 
        });
        
        var drinkVars =
        {
          key: drink.get("key"),
          name: drink.get("name"),
          description: drink.get("description"),
          imagePath: drink.get("imagePath"),
          ingredients: ingredientHtml
        };
        
        // DEBUG
        //console.log(drinkVars);

        // Populate the drink template
        var drinkTemplatePopulated = drinkTemplate(drinkVars);

        $("#content").append(drinkTemplatePopulated);
        
        // DEBUG
        console.log('rendered');
      });
    }
  });
  
  view = new DrinkView();
  drinks.fetch();
  view2 = new CategoryTopbarView({ el: $(".category-topbar"), 
                                   collection: categories });
  categories.fetch();

});
