<?php
/**
 * @file
 * Extensions to the Hosting service class for the web cluster module.
 */

module_load_include('service.inc', 'hosting_web_server');

class hostingService_http_cluster extends hostingService_http {
  public $type = 'cluster';

  function view(&$render) {
    $render['web_servers'] = array(
      '#type' => 'item',
      '#title' => t('Web servers'),
      '#markup' => theme('item_list', array('items' => array_map('_hosting_node_link', array_intersect_key($this->web_servers, hosting_get_servers('http'))))),
    );
  }

  function form(&$form) {
    parent::form($form);

    $servers = hosting_get_servers('http');
    if (isset($this->server->nid)) {
      unset($servers[$this->server->nid]);
    }

    $form['web_servers'] = array(
      '#title' => t('Servers'),
      '#type' => 'checkboxes',
      '#options' => $servers,
      '#default_value' => isset($this->web_servers) ? $this->web_servers : array(),
    );
  }

  function load() {
    parent::load();

    $ssl_enabled = TRUE;

    $web_servers = array();
    $result = db_query('SELECT web_server_nid FROM {hosting_web_cluster} WHERE vid = :vid', array(':vid' => $this->server->vid));
    while ($web_server = $result->fetch()) {
      $web_servers[] = $web_server->web_server_nid;
      $server = node_load($web_server->web_server_nid);
      $ssl_enabled = $ssl_enabled && $server->services['http']->ssl_enabled;
    }

    $this->ssl_enabled = $ssl_enabled;
    $this->setValues(array('web_servers' => drupal_map_assoc($web_servers)));
  }

  function insert() {
    parent::insert();
    foreach (array_filter($this->web_servers) as $web_server) {
      $record = array(
        'nid' => $this->server->nid,
        'vid' => $this->server->vid,
        'web_server_nid' => $web_server,
      );
      drupal_write_record('hosting_web_cluster', $record);
    }
  }

  function delete() {
    parent::delete();
    db_delete('hosting_web_cluster')
      ->condition('nid', $this->server->nid)
      ->execute();
  }

  function delete_revision() {
    parent::delete_revision();
    db_delete('hosting_web_cluster')
      ->condition('vid', $this->server->vid)
      ->execute();
  }

  function context_options($task_type, $ref_type, &$task) {
    parent::context_options($task_type, $ref_type, $task);

    $task->context_options['cluster_web_servers'] = implode(',', array_values(array_map('hosting_context_name', array_intersect_key($this->web_servers, hosting_get_servers('http')))));
  }
}
