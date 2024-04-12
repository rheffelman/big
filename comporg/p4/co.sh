for ((i=1; i<=360; i++))
do
    for ((ii=1; ii<=10; ii++))
    do
        cvsOutput=$(./cvs.exe $i $ii)
        myOutput=$(./a.out $i $ii)

        if [ "$cvsOutput" != "$myOutput" ]; then
            echo "Different outputs for x=$i and y=$ii"
            echo "my output: $myOutput"
            echo "his output: $cvsOutput"
            echo ""
        fi
    done
done