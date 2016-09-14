#!/bin/sh

echo 'set nu'        >> ~/.vimrc
echo 'set hlsearch'  >> ~/.vimrc
echo 'syntax on'     >> ~/.vimrc
echo 'set ts=4'      >> ~/.vimrc
echo 'set expandtab' >> ~/.vimrc

#autocmd BufReadPost *  if line("'\"")>0&&line("'\"")<=line("$") | exe "normal g'\"" |  endif
