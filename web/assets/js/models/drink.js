$(function()
{
  //-------------------------------------
  // This model describes a single drink
  //-------------------------------------
  Drink = Backbone.Model.extend(
  {
    defaults: 
    {
      name: "Not Specified",
      description: "Not Specified",
      key: "NIL",
      ingredients: "NIL",
      imagePath: "NIL",
      imageLicense: "NIL",
      imagePhotographer: "NIL",
      imageSource: "NIL"
    },
    initialize: function()
    {
      console.log('initialized drink: ' + this.get("name"));
    }
  });

  //--------------------------------------------------------
  // This is a collection of drinks fetched from the server
  //--------------------------------------------------------
  AllDrinks = Backbone.Collection.extend(
  {
      model: Drink,
      category_title: "All",
      url:"drinkList"
  });

  FlavorQuestions = [
      "WHAT IS YOUR DATE OF MANUFACTURE?",
      "KISS MY SHINY METAL ______!",
      "With my last breath, I curse ______!",
      "I'M GONNA DRINK 'TILL I ______!",
      "EXTERMINATE. EXTERMINATE! EXTERMINATE!!!",
      "WHAT IS YOUR QUEST?",
      "WHAT IS YOUR FAVORITE COLOR?",
      "WHAT GOES AROUND THE WORLD BUT STAYS IN A CORNER?",
      "WHAT IS PUT ON A TABLE, CUT, BUT NEVER EATEN?",
      "TO ALCOHOL, THE CAUSE AND SOLUTION TO ALL OF LIFE'S _____!" ];

  FlavorConfirms = [
      "Thank you for your order, <NAME>!",
      "EXTERMINATE. EXTERMINATE! EXTERMINATE!!!",
      "All our drink are belong to <NAME>.",
      "<NAME>: Sending directives to meat puppets.",
      "<NAME>. <NAME>. <NAME>.",
      "Excelent choice <NAME>.<br/> <ORDER> is the second best drink there is.",
      "We aim to serve the <NAME>.",
      "Your <ORDER> is currently being processed <br/> by my human appendages.",
      "The <ORDER>? <br/> Well, at least you know your limits.",
      "It's a pleasure to intoxicate the <NAME>.",
      "The <ORDER> huh? <br> What are you compensating for <NAME>?",
      "Oh No. <ORDER>, again? <br/> This is becoming a pain in my diodes.",
      "<NAME>, your order is of the utmost importance to us." ];

  function getFlavorText(name, drink){
     var rawMessage = FlavorConfirms[Math.floor(Math.random()*FlavorConfirms.length)];
     rawMessage = rawMessage.replace(/<NAME>/g, name);
     rawMessage = rawMessage.replace(/<ORDER>/g, drink.get('name'));
     return rawMessage;
  }

  //--------------------------------------------------------
  // This view renders a drink modal
  //--------------------------------------------------------
  DrinkModal = Backbone.View.extend(
  {
    model: Drink,
    render: function()
    {
      // DEBUG
      //console.log("Rendering Modal");
      
      var modalTemplate = _.template($("#modal_template").html());
      this.$el.html(modalTemplate(this.model));
      
      $("#modal_container").html(this.$el);
      $("#order_modal").on("shown", function(){ $("#customer").focus() });
      $("#order_modal").modal();
      
      $(window).on('hashchange', function() { $("#order_modal").modal('hide'); } );
    },
    events:
    {
      'click .click-to-order' : 'order',
      'submit #modal-form' : 'order'
    },
    order: function()
    { 
      var drink = this.model;
      $.ajax(
      {
        type: "GET",
        url: "orderPresetDrink",
        data: 
        {
          key: this.model.get("key"),
          customer: ( $("#order_modal").find("#customer").val() )
        },
        success: function(res)
        {
          if (res.result == true)
          {
            console.log("Order placed sucessfully");
            var customername = $("#order_modal").find("#customer").val();

            $("#order_modal").modal("hide");
            $("#splash").fadeIn({
                duration: 800   
            });

            console.log(drink);

            $("#splash-text").html(
                getFlavorText(customername, drink)
            );

          }
          else
          {
            console.log("Order could not be placed");
            alert("Have you ever considered a robotic implant?");
          }
        },
        error: function()
        {
          console.log("Order failed");
        }
      });

      return false;
    }
  });
  //--------------------------------------------------------
  // This view renders a single drink
  //--------------------------------------------------------
  DrinkView = Backbone.View.extend(
  {
    tagName: 'div',
    model: Drink,
    template: function()
    { 
      return _.template($("#drink_template").html()); 
    },
    events:
    {
      'click .click-to-modal' : 'modal'
    },
    modal: function()
    { 
      modal = new DrinkModal({model: this.model});
      modal.render();
    },
    render: function()
    {
      console.log("Making " + this.model.get("key"));
      var ingredients = this.model.get("ingredients");
      var ingredientHtml = '';
      var ingredientTemplate = _.template($("#ingredient_template").html());
      var drinkTemplate = _.template($("#drink_template").html()); 

      $("#drinks-list li").removeClass("selected");
      $("#drinks-list ." + this.model.get("key")).addClass("selected");

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
        imageLicense: this.model.get("imageLicense"),
        imagePhotographer: this.model.get("imagePhotographer"),
        imageSource: this.model.get("imageSource"),
        ingredients: ingredientHtml
      }

      var drinkTemplatePopulated = drinkTemplate(drinkVars);
      this.$el.html(drinkTemplatePopulated);
      
      $("#content").append(this.$el);
      $(".drink-popover").popover();

      return this;
    }
  });

  DrinkListView = Backbone.View.extend(
  {
    tagName:'ul',
    collection:AllDrinks,
    initialize: function()
    {
      var self = this;
      this.collection.on(
      {
        "sync": function() { self.render() }
      });
    },
    render: function()
    {
      var drinkListItemTemplate = _.template($("#drink_list_item_template").html());
      var list = $("#drinks-list");
      this.collection.each(function(drink, i)
      { 
        var poped = drinkListItemTemplate(drink);
        list.append(poped);
        $("#preload").append("<img src=\"" + drink.get("imagePath") + "\" width=\"1\" height=\"1\"/>");
      });

      this.setElement($("#drinks-list"));
    },
    events: 
    {
      'click .drink-list-item' : function(ev)
      { 
        window.location.hash = $(ev.target).attr("href");
        console.log("list click event recieved");
      }
    }
  });
});
