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
        //Foo
    }
  });

  DrinkList = Backbone.Collection.extend(
  {
    model: Drink,
    url: "assets/json/drinks.json"
  });

  drinks = new DrinkList();
 
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

