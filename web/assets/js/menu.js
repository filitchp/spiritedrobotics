$(function() 
{
  
  drinks = new AllDrinks();
  categories = new ValidCategories();

  //-------------------------------
  // This draws the menu of drinks
  //-------------------------------  
  DrinksView = Backbone.View.extend(
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
      // Clear the menu
      $("#drinks-list").empty();
      $(".category_title").html(this.collection.category_title);

      // For each drink
      this.collection.each(function(drink)
      {
        console.log("Rendering drink" + drink.toString());
        v = new DrinkView({model: drink});
        v.render();
      });
    }
  });
  
  view = new DrinksView();
  drinks.fetch();
  view2 = new CategoryTopbarView({ el: $(".category-topbar"), 
                                   collection: categories });
  categories.fetch();

});
