$(function()
{
    //------------------------------
    // This model describes a valid drink category
    //------------------------------
    Category = Backbone.Model.extend(
    {
        defaults: {
            name: "The Null Set",
            key: "NIL",
            description: "You were never here",
        },
        initialize: function(){
            console.log('initialized category: ' + this.get("name"));
        }
    });
    
    ValidCategories = Backbone.Collection.extend(
    {
        model: Category,
        url: "assets/json/categories.json"
    });

    CategoryTopbarView = Backbone.View.extend(
    {
        initialize: function(){
            console.log("Initialize topbar");
            var self = this;
            this.collection.on({
                "sync": function(){ self.render() }
            });
        },
        render: function(){
            var template = _.template( $("#topbar_template").html());
            var html = "";
            this.collection.each( function(element, index){
                html = html + template(element);
            });
            $(this.el).html(html);
        }
    });
});
