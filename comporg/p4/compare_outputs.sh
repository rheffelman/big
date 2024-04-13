for ((i=1; i<=10000; i++))
do
    x=$(awk -v min=-1000 -v max=1000 'BEGIN{srand(); printf "%.2f\n", min+rand()*(max-min)}')
    y=$(( ( RANDOM % 10 )  + 1 ))
    cvs_output=$(./cvs.exe $x $y)
    a_out_output=$(./p4final.exe $x $y)

    if [ "$cvs_output" != "$a_out_output" ]; then
        echo "Different outputs for x=$x and y=$y"
        echo "my output: $a_out_output"
        echo "his output: $cvs_output"
        echo ""
    fi
done