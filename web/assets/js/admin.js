$(function()
{
    orders = new PendingOrders();
    view = new PendingOrdersView({collection: orders});
    orders.fetch();
    view2 = new DebugView();
    view2.render();

    window.setInterval(function(){ orders.fetch() } , 3000 );

    $(".foo_button").on('click', function(ev){ alert(ev.target.id) } );
});
