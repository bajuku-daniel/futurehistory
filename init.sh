#!/usr/bin/env bash


#git pull origin dev
mkdir -p ../db_backup
drush sql-dump > ../db_backup/$(date +"%Y-%m-%d__%H-%M-%S".sql)

## delete old unsused module references - module has been deleted somewhen
#drush sql-query "DELETE from system where name = 'mass_contact' AND type = 'module';"
#drush sql-query "DELETE from system where name = 'user_restrictions_ui' AND type = 'module';"
#drush sql-query "DELETE from system where name = 'user_restrictions' AND type = 'module';"


## delete menu link 626 :)
drush ev "menu_link_delete(626);"
drush ev "module_load_include('inc', 'locale', 'menu');menu_link_delete(626);"


echo "##################  menu item"

drush dl -y strongarm
drush en -y strongarm
echo "##################  strongarm"
drush dl -y features
drush en -y features
echo "##################  features"
drush dl -y diff
drush en -y diff
echo "##################  diff"
drush dl -y autocomplete_deluxe
drush en -y autocomplete_deluxe
echo "##################  autocomplete_deluxe"
drush dl -y field_placeholder 7.x-2.0-beta2
drush en -y field_placeholder
echo "##################  field_placeholder"
drush en -y fu_hilfetexte
drush en -y fu_ansicht
echo "##################  fu_hilfetexte && fu_ansicht"

drush cc all

drush fr -y fu_hilfetexte
drush fr -y fu_ansicht

#drush user-password Romalu3 --password="test"
drush user-create rafael --mail="rafael.hiss@gmail.com" --password="rafael_fuhi_2016"
drush user-create test --mail="test@test.com" --password="test"


cp patches/autocomplete_deluxe-count-sort.patch ../autocomplete_deluxe/autocomplete_deluxe-count-sort.patch
cd .. && cd autocomplete_deluxe && patch < autocomplete_deluxe-count-sort.patch
echo "##################  PATCH"


drush cc all