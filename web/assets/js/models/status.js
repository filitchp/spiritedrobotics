$(function()
{
  
  SystemStatus = Backbone.Model.extend(
  {
    defaults: 
    {
      status: "Unknown"
    },
    url: "systemStatus"
  });
  
  //----------------------------------
  //  View to display system status
  //----------------------------------
  SystemStatusView = Backbone.View.extend(
  {
    tagName: 'div',
    model: SystemStatus,
    initialize: function()
    {
      var self = this;
      
      this.model.on(
      {
        // Everytime the model changes the view will be rendered
        "sync": function(){ self.render(); }
      });
    },
    render: function()
    {
      // DEBUG
      //console.log("Rendering StatusView> " + this.model.get("status"));
      
      var unrenderedTemplate;
      
      if (this.model.get("status") === "Idle")
      {
        unrenderedTemplate = _.template($("#status_success_template").html());
      }
      else
      {
        unrenderedTemplate = _.template($("#status_important_template").html());
      }
             
      this.$el.html(unrenderedTemplate(this.model));
      $("#system-status-container").append(this.$el);
      
      return this;
    }
  });
});
