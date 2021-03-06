$(function()
{
  // Create a collection of pending orders
  pendingOrders = new PendingOrders();
 
  // Create the view to display the pending orders
  pendingOrdersView = new PendingOrdersView({collection: pendingOrders});
  pendingOrders.fetch();
  
  // View with controls for calibrating and debugging the system
  debugView = new DebugView();
  debugView.render();
  
  qucikAccessButtonView = new QuickAccessButtonView();
  qucikAccessButtonView.render();
  
  // Create the system status model
  systemStatus = new SystemStatus();
  systemStatus.fetch();

  // Create the approved orders list
  approvedOrders = new ApprovedOrders();
  approvedOrders.fetch();
  
  // System status view
  systemStatusView = new SystemStatusView({ model: systemStatus });

  // Update order on a timer
  window.setInterval(function(){ pendingOrders.fetch() } , 1000 );
  window.setInterval(function(){ approvedOrders.fetch() } , 1000 );
  
  // Update system status on a timer
  window.setInterval(function(){ systemStatus.fetch() } , 1000 );
});
