#!/usr/bin/env bash

#mkdir -p ../../../../../db_backup
drush sql-dump > ../../../../../db_backup/$(date +"%Y-%m-%d__%H-%M-%S".sql)
#drush sql-drop -y
#drush sql-cli < ../../../../../db_backup/2017-04-28__16-15-01_from_live.sql



git pull origin master
cd ../../themes/future_history/ && git pull origin master && cd -
cd ../futurehistory_entdecken/ && git pull origin master && cd -
drush cc all


drush cc all
drush dis -y overlay
drush en -y map_view_update
drush fr -y map_view_update

#drush user-password Romalu3 --password="test"

drush cc all
