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
          "sync": function(){ self.setHash(window.location.hash) }
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
      console.log("Rendering menu idx: " + idx.toString());
      $("#content").empty();
      // Clear the menu
      $(".category_title").html(this.collection.category_title);
      // Render a drink 
      var drink = this.collection.at(idx); 

      if (drink != null){
        window.location.hash = "#" + drink.get('key');  
        v = new DrinkView({model: drink});
        v.render();
      }
    },
    setHash: function(hash){
        var idx = 0;
        
        if(hash != ""){
          var target = this.collection.where({ key: hash.substring(1) });
          console.log(hash);
          idx = this.collection.indexOf(target[0]);
        }

          this.current_index = idx;
          this.render(idx);
    },
    getHash: function(idx){
        var target = this.collection.at(idx);
        return target.get("key");
    }
  });
  
  view = new DrinksView({ collection: drinks });
  drinks.fetch();
  view3 = new DrinkListView({ collection: drinks, target: view});
  view2 = new CategoryTopbarView({ el: $(".category-topbar"), 
                                   collection: categories });
  
 $(window).on('hashchange', function(){
    view.setHash(window.location.hash);
 });

  categories.fetch();
    
  $("#splash").show();
  $("#splash").click(function(){
    $("#splash").fadeOut({
        duration: 800   
    });
  });

});
