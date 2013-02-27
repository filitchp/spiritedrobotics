$(function()
{
    //------------------------------------
    // This model describes a single order
    //------------------------------------
    Order = Backbone.Model.extend(
    {
        defaults: {
            customer: "Pat Doe",
            key: "NIL",
            ingredients: "NIL",
            date: function(){ return new Date.getTime(); } 
        },
        initialize: function(){
            console.log('initialized order: ' + this.get("customer"));
        }
    });

    //------------------------------------
    // This is a collection of orders
    //------------------------------------
    PendingOrders = Backbone.Collection.extend(
    {
        model: Order,
        url:"pendingOrders"
    });

    ApprovedOrders = Backbone.Collection.extend(
    {
        model: Order,
        url:"approvedOrders"
    });

    MyOrders = Backbone.Collection.extend(
    {
        model: Order
    });

    OrderView = Backbone.View.extend(
    {
        tagName: 'div',
        model: Order,
        render: function(){
            console.log("Rendering order> " + this.model.get("customer") + ": " + this.model.get("key"));
            var unrenderedTemplate = _.template($("#order_template").html());
            var renderedTemplate = unrenderedTemplate(this.model);
            $("#orders-list").append(renderedTemplate);
        }
    });

    PendingOrdersView = Backbone.View.extend(
    {
        collection: PendingOrders,
        initialize: function(){
            var self = this;
            this.collection.on({
                "sync": function(){ self.render(); }
            });
        },
        render: function(){
            this.collection.each(function(ord){
               var v = new OrderView({model: ord});
               v.render();
            });
        }
    });
});
