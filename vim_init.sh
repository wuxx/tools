#!/bin/sh

cat << EOF >> ~/.vimrc
set nu
set hlsearch
syntax on
set ts=4
set expandtab
set sw=4
set cindent
set smarttab
set incsearch

autocmd BufReadPost *  if line("'\"")>0&&line("'\"")<=line("$") | exe "normal g'\"" |  endif

EOF
