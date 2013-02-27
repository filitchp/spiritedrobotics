$(function()
{
    orders = new PendingOrders();
    view = new PendingOrdersView({collection: orders});
    orders.fetch();
    view2 = new DebugView();
    view2.render();
});
