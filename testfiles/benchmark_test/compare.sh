#!/bin/sh

# ファイル全部読み取ってリストに格納
ft_file=(`cat ./output/ft_benchmark.txt | xargs`)
std_file=(`cat ./output/std_benchmark.txt | xargs`)

printf "%-30s %15s %15s %10s\n" func_name ft_time std_time ratio

# 一行ずつ処理するループ
for ((i=0; i<${#ft_file[@]}; i++)); do

	# 一行文取得
	ft_line=${ft_file[i]}
	std_line=${std_file[i]}

	# 取得した一行をカンマで分割し、リストに格納
	ft_line_list=(${ft_line//,/ })
	std_line_list=(${std_line//,/ })

	# func_name, ft_time, std_time, ratio 出力
	func_name=${ft_line_list[0]}
	ft_time=${ft_line_list[1]}
	std_time=${std_line_list[1]}
	ratio=`echo "scale=3; ${ft_time} / ${std_time}" | bc`
	printf "%-30s %15s %15s %10s\n" $func_name $ft_time $std_time $ratio

done
