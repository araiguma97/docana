for file in `\find . -type f`; do
    nkf --overwrite -w -Lu $file
    echo $file
done
