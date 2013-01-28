$(function() 
{

  drinks = new AllDrinks();
 
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
      $("#drinks-list").empty();
      this.collection.each(function(value){
        $("#drinks-list").append("<li><a href=\"#" + value.get("key") + "\">" + value.get("name") + "</a></li>");
        console.log('rendered');
      });
    }
  });

  view = new DrinkView();
  drinks.fetch();
});

