#!/usr/bin/env bash

git pull origin dev

mkdir -p ../../../../../db_backup
drush sql-dump > ../../../../../db_backup/$(date +"%Y-%m-%d__%H-%M-%S".sql)
drush fr map_view_update
cd ../../themes/future_history/ && git pull origin dev && cd -
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