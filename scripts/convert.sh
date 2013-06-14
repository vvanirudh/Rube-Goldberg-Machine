#!/bin/bash
cd plots_doc
for f in *.png
do
    convert "$f" "${f/%png/eps}"
done
