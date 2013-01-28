$(function() 
{
  FriendList = Backbone.Collection.extend(
  {
    initialize: function()
    {
    }
  });

  FriendView = Backbone.View.extend(
  {
    tagName: 'li',
    events:
    {
      'click #add-input': 'getFriend',
    },
    initialize: function() 
    {
      var thisView = this;
      this.friendslist = new FriendList;
      
      _.bindAll(this, 'render');
      
      this.friendslist.bind("add", function(model)
      {
        //alert("hey");
        thisView.render(model);
      })
    },
    getFriend: function()
    {
      var friend_name = $('#input').val();
      this.friendslist.add({name: friend_name});
    },
    render: function(model)
    {
      $("#friends-list").append("<li>" + model.get("name") + "</li>");
      console.log('rendered');
    }
  });

  var view = new FriendView({el: 'body'});
});