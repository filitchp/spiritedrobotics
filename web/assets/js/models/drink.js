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

    //--------------------------------------------------------
    // This view renders a drink modal
    //--------------------------------------------------------
    DrinkModal = Backbone.View.extend(
    {
        model: Drink,
        render: function(){
            console.log("Rendering Modal");
            var modalTemplate = _.template($("#modal_template").html());
            this.$el.html(modalTemplate(this.model));
            $("#modal_container").html(this.$el);
            $("#order_modal").on("shown", function(){ $("#customer").focus() });
            $("#order_modal").modal();
            $(window).on('hashchange', function() { $("#order_modal").modal('hide'); } );
        
        },
        events: {
            'click .click-to-order' : 'order',
            'submit #modal-form' : 'order'
        },
        //TODO replace this with creating an order and posting it...
        order: function(){ 
            $.ajax({
                type: "GET",
                url: "orderPresetDrink",
                data: {
                    key: this.model.get("key"),
                    customer: ( $("#order_modal").find("#customer").val() ) //+ " " + 
                 //   $("#order_modal").find("#flavor").val() )
                },
                success: function(res){
                    if (res.result == true){
                        console.log("Order placed sucessfully");
                        
                      //  newOrder = new Order({ 
                      //      key: this.model.get("key"),
                      //      customer: $("#order_modal").find("#customer").val(),
                      //      timestamp: res.timestamp
                      //  });
                      // MyOrders.add(newOrder);

                        window.location = "";
                        $("#order_modal").modal("hide");
                    }else{
                        console.log("Order could not be placed");
                        alert("Have you ever considered a robotic implant?");
                    }
                },
                error: function(){
                    console.log("Order failed");
                }
            });
        }
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
            'click .click-to-modal' : 'modal'
        },
        modal: function() { 
                modal = new DrinkModal({model: this.model});
                modal.render();
        },
        render: function(){
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
                ingredients: ingredientHtml
            }

            var drinkTemplatePopulated = drinkTemplate(drinkVars);
            this.$el.html(drinkTemplatePopulated);
            $("#content").append(this.$el);
            return this;
        }
    });
	
    DrinkListView = Backbone.View.extend({
        tagName:'ul',
        collection:AllDrinks,
        initialize: function() {
            var self = this;
            this.collection.on({
                "sync": function() { self.render() }
            });
        },
        render: function() {
            var drinkListItemTemplate = _.template($("#drink_list_item_template").html());
            var list = $("#drinks-list");
            this.collection.each(function(drink, i){ 
                var poped = drinkListItemTemplate(drink);
                list.append(poped);
                $("#preload").append("<img src=\"" + drink.get("imagePath") + "\" width=\"1\" height=\"1\"/>");
            });
            this.setElement($("#drinks-list"));
        },
        events: {
            'click .drink-list-item' : function(ev){ 
                window.location.hash = $(ev.target).attr("href");
                console.log("list click event recieved");
            }
        }
    });
});
