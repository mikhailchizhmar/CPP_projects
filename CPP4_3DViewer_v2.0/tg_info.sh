#!/bin/bash
set -e

branch=$1
job=$2
status=$3

source ~/.bashrc
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="$branch $job $status"
curl -s --max-time 1 -d "chat_id=$TELEGRAM_CHAT_ID&disable_web_page_preview=1&text=$TEXT" $URL
curl -s --max-time 1 -d "chat_id=$TELEGRAM_CHAT_ID2&disable_web_page_preview=1&text=$TEXT" $URL

# curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null