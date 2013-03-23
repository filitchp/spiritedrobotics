$(function() 
{
  
  drinks = new AllDrinks();
  categories = new ValidCategories();

  //-------------------------------
  // This draws the menu of drinks
  //-------------------------------  
  DrinksView = Backbone.View.extend(
  {
    tagName: 'ul',
    collection: drinks,
    events: {
        'click .next-drink' : 'nextDrink',
        'click .prev-drink' : 'prevDrink'
    },
    initialize: function()
    {
      var self = this;
      this.current_index = 0;
      this.setElement($("body"));
      this.collection.on({
          "sync": function(){ self.render(0) }
      });
    },
    current_index: 0,
    nextDrink: function(){
        this.current_index = this.current_index + 1;
        if (this.current_index > this.collection.size() - 1){
            this.current_index = 0;
        }
        this.render(this.current_index);
    },
    prevDrink: function(){
        this.current_index = this.current_index - 1;
        if (this.current_index < 0){
            this.current_index = this.collection.size() - 1;
        }
        this.render(this.current_index);
    },
    render: function(idx)
    {
      $("#content").empty();
      // Clear the menu
      $(".category_title").html(this.collection.category_title);
      // Render a drink
        v = new DrinkView({model: this.collection.at(idx)});
        v.render();
    },
    setHash: function(hash){
        var target = this.collection.where({ key: hash.substring(1) });
        console.log(hash);
        var idx = this.collection.indexOf(target[0]);
        this.current_index = idx;
        this.render(idx);
    }
  });
  
  view = new DrinksView();
  view3 = new DrinkListView({ collection: drinks, target: view});
  drinks.fetch();
  view2 = new CategoryTopbarView({ el: $(".category-topbar"), 
                                   collection: categories });
  
 $(window).on('hashchange', function(){
    view.setHash(window.location.hash);
 });


  categories.fetch();

});
