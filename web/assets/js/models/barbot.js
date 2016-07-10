$(function()
{
  //----------------------------------------
  // This model describes the BarBot system
  //----------------------------------------
  Barbot = Backbone.Model.extend(
  {
    defaults:
    {
      //??????
    },
    initialize: function()
    {
      console.log('initialized barbot: ' + '??????');
    }
  });

  DebugView = Backbone.View.extend(
  {
    tagName: 'div',
    model: Barbot,
    events:
    {
      'click .click-to-test': 'test',
      'click .click-passive-lights': 'passiveLights',
      'click .click-fire-lights': 'fireLights',
      'click .click-fire-tower' : 'testTower',
      'click .click-to-set-intensity' : 'setIntensity'
    },
    testTower: function(ev)
    {
      var towerindex = $(ev.target).data("towerindex");
      $.ajax(
      {
        type: "GET",
        url: "testTower",
        data:
        {
          tower: towerindex,
          amount: 0.4
        },
        success: function(res)
        {
          if (res.result !== true)
          {
            alert("test error");
          }
        },
        error: function(data)
        {
          alert("test error");
          console.log(data);
        }
      });
    },
    setIntensity: function()
    {
      $.ajax(
      {
        type: "GET",
        url: "setIntensity",
        data:
        {
          intensity: $("#intensity_number").val()
        },
        success: function(res)
        {
          if (res.result !== true)
          {
            alert("intensity error");
          }
        },
        error: function(data)
        {
          alert("intensity error");
          console.log(data);
        }
      });
    },
    test: function()
    {
      $.ajax(
      {
        type: "GET",
        url: "testTower",
        data:
        {
          tower: $("#test_number").val(),
          amount: $("#test_amount").val()
        },
        success: function(res)
        {
          if (res.result !== true)
          {
            alert("test error");
          }
        },
        error: function(data)
        {
          alert("test error");
          console.log(data);
        }
      });
    },
    passiveLights: function()
    {
      $.ajax(
      {
        type: "GET",
        url: "setLights?mode=0",
        success: function(res)
        {
          if (res.result !== true)
          {
            alert("passiveLights error");
          }
        },
        error: function(data)
        {
          alert("passiveLights error");
          console.log(data);
        }
      });
    },
    fireLights: function()
    {
      $.ajax(
      {
        type: "GET",
        url: "setLights?mode=1",
        success: function(res)
        {
          if (res.result !== true)
          {
            alert("fireLights error");
          }
        },
        error: function(data)
        {
          alert("fireLights error");
          console.log(data);
        }
      });
    },
    render: function()
    {
      var template = _.template($("#debug_template").html());
      this.$el.html(template());
      $("#debug-container").append(this.$el);
      return this;
    }
  });

  QuickAccessButtonView = Backbone.View.extend(
  {
    tagName: 'div',
    model: Barbot,
    events:
    {
      'click .click-to-init': 'init',
      'click .click-to-stop': 'stop'
    },
    stop: function() 
    {
      $.ajax(
      {
        type: "GET",
        url: "haltTowers",
        success: function(res)
        {
          if (res.result == true) 
          {
            console.log(res.toString());
          }
          else
          {
            alert("ERR");
          }
        }
      });
    },
    init: function()
    {
      $.ajax(
      {
        type: "GET",
        url: "initTowers",
        success: function(res)
        {
          if (res.result == true)
          {
            console.log(res.toString());
          }
          else
          {
            alert("ERR");
          }
        }
      });
    },
    render: function()
    {
      var template = _.template($("#quick_access_buttons_template").html());
      this.$el.html(template());
      $("#quick-access-buttons-container").append(this.$el);
      return this;
    }
  });
});
