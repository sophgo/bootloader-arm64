#!/bin/bash

FLAG_FILE="/var/.multimedia_self_check_done"

# If the marked file already exists, exit
if [ -f "$FLAG_FILE" ]; then
    echo "bmrt_setup.sh already executed on first boot. Exiting."
    exit 0
fi

# Cleanup function: Kill all background processes
cleanup() {
    kill $(jobs -p) 2>/dev/null
}

trap cleanup EXIT

# Function to run commands and display progress bars
run_command() {
    local cmd="$1"
    local desc="$2"
    local current="$3"
    local total="$4"
    local tempfile=$(mktemp)

    # Display command description and initial progress bar with progress count
    printf " [ ] (%d/%d) %-45s" "$current" "$total" "$desc"

    # Start rotating progress bar
    (
        while :; do
            for c in '|' '/' '-' '\\'; do
                printf "\r [%s] (%d/%d) %s" "$c" "$current" "$total" "$desc"
                sleep 0.1
            done
        done
    ) & local spinner_pid=$!

    # recording start time
    local start_time=$(date +%s)

    # Execute commands and capture output
    eval "$cmd" > "$tempfile" 2>&1
    local exit_status=$?

    # Calculate execution time
    local end_time=$(date +%s)
    local duration=$((end_time - start_time))

    # Stop progress bar
    kill $spinner_pid 2>/dev/null
    wait $spinner_pid 2>/dev/null

    # Display results
    if [ $exit_status -eq 0 ]; then
        printf "\r \033[32m[  ok  ]\033[0m (%d/%d) %-45s " \
            "$current" "$total" "$desc"
        printf "\033[32m(pass, %ds)\033[0m\n" "$duration"
    else
        printf "\r \033[31m[ fail ]\033[0m (%d/%d) %-45s " \
            "$current" "$total" "$desc"
        printf "\033[31m(fail, %ds)\033[0m\n" "$duration"
        echo "Command output:"
        cat "$tempfile"
        echo -e "\n----------------------------------------"
    fi

    # Clean up temporary files
    rm -f "$tempfile"

    return $exit_status
}

# Main execution logic
echo "         Starting Multimedia hardware self-test..."

total_tests=6
current_test=1

run_command "/opt/sophon/libsophon-current/bin/test_cv_warp_affine" \
    "test_cv_warp_affine" "$current_test" "$total_tests"
result1=$?
current_test=$((current_test+1))

run_command "/opt/sophon/libsophon-current/bin/test_cv_gaussian_blur 1 1 1 1920 1080 8 3 0.092916 0.479358" \
    "test_cv_gaussian_blur" "$current_test" "$total_tests"
result2=$?
current_test=$((current_test+1))

run_command "/opt/sophon/libsophon-current/bin/bm1684x/test_bm1684x_vpp_convert 1920 1080 \
    0 /opt/sophon/libsophon-current/bin/image/vpp_input/i420.yuv 0 0 1920 1080 1920 1080 \
    10 rgb24.bin 0 1 0 8 csc_scale.csv" \
    "test_bm1684x_vpp_convert" "$current_test" "$total_tests"
result3=$?
current_test=$((current_test+1))

run_command \
    "/opt/sophon/libsophon-current/bin/bmvpuenc -c 0 -f 1 -w 1920 -h 1080 \
    -i /opt/sophon/libsophon-current/bin/image/venc_test.yuv -o vdec_test" \
    "bmvpuenc" "$current_test" "$total_tests"
result4=$?
current_test=$((current_test+1))

run_command "/opt/sophon/libsophon-current/bin/bm_test --input vdec_test-0.264 --instance 4" \
    "bm_test" "$current_test" "$total_tests"
result5=$?
current_test=$((current_test+1))

run_command \
    "/opt/sophon/sophon-opencv-latest/bin/jpumulti 3 \
    /opt/sophon/libsophon-current/bin/image/1920_420.jpg 50 16 1 0" \
    "jpumulti" "$current_test" "$total_tests"
result6=$?

# Final Status Summary
echo "         Multimedia hardware self-test result:"
tpu_status=$([[ $result1 -eq 0 && $result2 -eq 0 ]] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         TPU:  $tpu_status"

vpp_status=$([ $result3 -eq 0 ] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         VPP:  $vpp_status"

venc_status1=$([ $result4 -eq 0 ] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         VENC: $venc_status1"

venc_status2=$([ $result5 -eq 0 ] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         VENC: $venc_status2"

venc_status3=$([ $result6 -eq 0 ] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         VENC: $venc_status3"

# Clean up generated files
rm -rf csc_scale.csv* rgb24.bin_thread*

[ $result1 -ne 0 ] || \
[ $result2 -ne 0 ] || \
[ $result3 -ne 0 ] || \
[ $result4 -ne 0 ] || \
[ $result5 -ne 0 ] || \
[ $result6 -ne 0 ] && exit 1

# Create a tag file after execution is complete
touch "$FLAG_FILE"

exit 0
