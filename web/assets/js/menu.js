$(function() 
{
  Drink = Backbone.Model.extend(
  {
    defaults: {
        name: "Not Specified",
        description: "Not Specified",
        key: "NIL"
    },
    initialize: function(){
        //Foo
    }
  });

  DrinkList = Backbone.Collection.extend(
  {
    model: Drink
  });

  var drink1 = new Drink({name: "Rum and Coke", description: "Best drink", key:"RC"});
  var drink2 = new Drink({name: "Rum and Tonic", description: "Second Best drink", key:"RT"});
  var drink3 = new Drink({name: "Rum and Rum", description: "Really The Best drink", key:"R"});

  drinks = new DrinkList([drink1,drink2,drink3]);

  DrinkView = Backbone.View.extend(
  {
    tagName: 'li',
    initialize: function(){
      this.render();
    },
    render: function()
    {
      this.collection.each(function(value){
        $("#drinks-list").append("<li><a href=\"#" + value.get("key") + "\">" + value.get("name") + "</a></li>");
        console.log('rendered');
      });
    }
  });

  view = new DrinkView({el: 'body', collection: drinks});
  
});
