api = 2

core = 7.x
projects[] = "drupal"

projects[webform_civicrm][subdir] = contrib
projects[views][subdir] = contrib
projects[ctools][subdir] = contrib

# Other useful modules:
# projects[admin_menu][subdir] = contrib
# projects[devel][subdir] = contrib

projects[civicrm][type] = "module"
projects[civicrm][directory_name] = "civicrm"
projects[civicrm][download][type] = "get"
projects[civicrm][download][url] = "https://download.civicrm.org/civicrm-4.7.6-drupal.tar.gz"

libraries[civicrm_l10n][destination] = "modules"
libraries[civicrm_l10n][directory_name] = "civicrm"
libraries[civicrm_l10n][download][type] = "get"
libraries[civicrm_l10n][download][url] = "https://download.civicrm.org/civicrm-4.7.6-l10n.tar.gz"
libraries[civicrm_l10n][overwrite] = TRUE
