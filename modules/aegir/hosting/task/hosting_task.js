(function($) {

hostingTaskRefreshList = function() {
  if (!Drupal.settings.hostingTaskRefresh.nid) {
    return null;
  }

  var hostingTaskListRefreshCallback = function(data, responseText) {
    // If the node has been modified, reload the whole page.
    if (Drupal.settings.hostingTaskRefresh.changed < data.changed) {
      // only reload if there is no modal frame currently open
      if ($(document).data('hostingOpenModalFrame') != true) {
        // If a specific URL was specified, go there.
        if (data.navigate_url) {
          document.location = data.navigate_url;
        }
        // Fall back to just doing a reload of the current page.
        else {
          document.location.reload();
        }
      }
    }
    else {
      $("#hosting-task-list").html(data.markup);

      hostingTaskBindButtons('#hosting-task-list');
      setTimeout("hostingTaskRefreshList()", 30000);
    }
  }

  hostingTaskAddOverlay('#hosting-task-list');
  $.get(Drupal.settings.basePath + 'hosting/tasks/' + Drupal.settings.hostingTaskRefresh.nid + '/list', null, hostingTaskListRefreshCallback , 'json' );
}


function hostingTaskAddOverlay(elem) {
  $(elem).prepend('<div class="hosting-overlay"><div class="hosting-throbber"></div></div>');
}


hostingTaskRefreshQueueBlock = function() {
  if (Drupal.settings.hostingTaskRefresh.queueBlock != 1) {
    return null;
  }

  var hostingTaskQueueRefreshCallback = function(data, responseText) {
    $("#block-views-hosting-task-list-block .content").html(data.markup);

    hostingTaskBindButtons('#block-views-hosting-task-list-block');
    setTimeout("hostingTaskRefreshQueueBlock()", 30000);
  }

  hostingTaskAddOverlay('#block-views-hosting-task-list-block .view-content');
  $.get(Drupal.settings.basePath + 'hosting/tasks/queue', null, hostingTaskQueueRefreshCallback , 'json');
}

$(document).ready(function() {
  $(document).data('hostingOpenModalFrame', false);
  setTimeout("hostingTaskRefreshList()", 30000);
  setTimeout("hostingTaskRefreshQueueBlock()", 30000);
  hostingTaskBindButtons($(this));
  $('#hosting-task-confirm-form-actions a').click(function() {
    if (parent.Drupal.modalFrame.isOpen) {
      setTimeout(function() { parent.Drupal.modalFrame.close({}, {}); }, 1);
      return false;
    }
  });

});

hostingTaskBindButtons = function(elem) {
  $('.hosting-button-dialog', elem).click(function() {
      $(document).data('hostingOpenModalFrame', true)
     var options = {
        url : Drupal.settings.basePath + 'hosting/js' + $(this).attr('href'),
        draggable : false,
        width : 600,
        height : 150,
        onSubmit : function() {
          $(document).data('hostingOpenModalFrame', false)
          hostingTaskRefreshQueueBlock();
          hostingTaskRefreshList();
        }
      }
      Drupal.modalFrame.open(options);
      return false;
   });
}


})(jQuery);
