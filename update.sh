#!/usr/bin/env bash

mkdir -p ../../../../../db_backup
drush sql-dump > ../../../../../db_backup/$(date +"%Y-%m-%d__%H-%M-%S".sql)
drush sql-drop -y
drush sql-cli < ../../../../../db_backup/2017-04-28__16-15-01_from_live.sql

git pull origin dev
cd ../futurehistory_entdecken/ && git pull origin dev_rh && cd -
cd ../../themes/future_history/ && git pull origin dev && cd -


drush cc all
drush dis -y overlay
drush fr -y map_view_update

drush user-password Romalu3 --password="test"

drush cc all


#mkdir -p ~/db_backup
#cp sites/default/files ~/db_backup/sites/default/files/
#mkdir -p ~/db_backup/sites/default/files/
#drush sql-dump > ~/db_backup/$(date +"%Y-%m-%d__%H-%M-%S".sql)
#drush sql-dump > ../../../../../db_backup/$(date +"%Y-%m-%d__%H-%M-%S".sql)
#drush sql-dump > ../db_backup/$(date +"%Y-%m-%d__%H-%M-%S".sql)
#drush sql-drop -y
#drush sql-cli < 2017-02-01__15-05-29.sql
#cd ../../themes/future_history/ && git pull origin dev && cd -
#sql-dump > ~/db_backup/$(date +"%Y-%m-%d__%H-%M-%S".sql)
