<?php
/**
 * @file
 * Expose the migrate feature to hostmaster.
 */

/**
 * Implements hook_hosting_feature().
 */
function hosting_migrate_hosting_feature() {
  $features['migrate'] = array(
    'title' => t('Site migration'),
    'description' => t('Migrate sites to platforms of the same or later version.'),
    'status' => HOSTING_FEATURE_ENABLED,
    'module' => 'hosting_migrate',
    'group' => 'optional',
    'role_permissions' => array(
      'aegir platform manager' => array(
        'create migrate task',
      ),
      'aegir client' => array(
        'create migrate task',
      ),
    ),
  );
  return $features;
}
