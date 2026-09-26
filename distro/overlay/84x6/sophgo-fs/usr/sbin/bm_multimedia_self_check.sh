#!/bin/bash

FLAG_FILE="/var/.multimedia_self_check_done"
LOG_FILE="/data/multimedia_self_check.log"

# If the marked file already exists, exit
if [ -f "$FLAG_FILE" ]; then
    echo "bmrt_setup.sh already executed on first boot. Exiting."
    exit 0
fi

mkdir -p "$(dirname "$LOG_FILE")"
> "$LOG_FILE"

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

    {
        if [ $exit_status -eq 0 ]; then
            printf "[  ok  ] (%d/%d) %s (pass, %ds)\n" \
                "$current" "$total" "$desc" "$duration"
        else
            printf "[ fail ] (%d/%d) %s (fail, %ds)\n" \
                "$current" "$total" "$desc" "$duration"
            echo "Command output:"
            cat "$tempfile"
            echo "----------------------------------------"
        fi
    } >> "$LOG_FILE"

    # Clean up temporary files
    rm -f "$tempfile"

    return $exit_status
}

{
    echo "========================================"
    echo "Multimedia hardware self-test started at: $(date)"
    echo "========================================"
} >> "$LOG_FILE"

# Main execution logic
echo "         Starting Multimedia hardware self-test..."

echo "         Starting Multimedia hardware self-test..." >> "$LOG_FILE"

total_tests=10
current_test=1

run_command "/opt/sophon/libsophon-current/bin/test_cv_warp_affine" \
    "test_cv_warp_affine" "$current_test" "$total_tests"
result1=$?
current_test=$((current_test+1))

run_command "/opt/sophon/libsophon-current/bin/test_vpss_convert_to 1920 1080 1.1 0.9 3.14159 10 20 -30 8 0" \
    "test_vpss_convert_to" "$current_test" "$total_tests"
result2=$?
current_test=$((current_test+1))

run_command "/opt/sophon/libsophon-current/bin/test_dpu_fgs_thread" \
    "test_dpu_fgs_thread" "$current_test" "$total_tests"
result3=$?
current_test=$((current_test+1))

run_command "/opt/sophon/libsophon-current/bin/test_dwa_rot_thread 1 1 1" \
    "test_dwa_rot_thread" "$current_test" "$total_tests"
result4=$?
current_test=$((current_test+1))

run_command "/opt/sophon/libsophon-current/bin/test_ldc_rot_thread 1 1 1" \
    "test_ldc_rot_thread" "$current_test" "$total_tests"
result5=$?
current_test=$((current_test+1))

run_command "/opt/sophon/libsophon-current/bin/test_ive_hist_thread 352 288 /opt/sophon/libsophon-current/bin/res/00_352x288_y.yuv \
             ./hist_res.bin /opt/sophon/libsophon-current/bin/res/sample_Hist.bin 0 1 1 0" \
    "test_ive_hist_thread" "$current_test" "$total_tests"
result6=$?
current_test=$((current_test+1))

run_command "/opt/sophon/libsophon-current/bin/test_tde_thread" \
    "test_tde_thread" "$current_test" "$total_tests"
result7=$?
current_test=$((current_test+1))

run_command \
    "/opt/sophon/libsophon-current/bin/bmvpuenc -c 0 -f 1 -w 1920 -h 1080 \
    -i /opt/sophon/libsophon-current/bin/res/venc_test.yuv -o vdec_test" \
    "bmvpuenc" "$current_test" "$total_tests"
result8=$?
current_test=$((current_test+1))

run_command "/opt/sophon/libsophon-current/bin/bm_test --input vdec_test-0.264 --instance 4" \
    "bm_test" "$current_test" "$total_tests"
result9=$?
current_test=$((current_test+1))

run_command \
    "/opt/sophon/sophon-opencv-latest/bin/jpumulti 3 \
    /opt/sophon/libsophon-current/bin/res/1920_420.jpg 50 16 1 0" \
    "jpumulti" "$current_test" "$total_tests"
result10=$?

# Final Status Summary
echo "         Multimedia hardware self-test result:"
tpu_status=$([[ $result1 -eq 0 ]] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         TPU:  $tpu_status"

vpss_status=$([ $result2 -eq 0 ] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         VPSS:  $vpss_status"

dpu_status=$([ $result3 -eq 0 ] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         DPU:  $dpu_status"

dwa_status=$([ $result4 -eq 0 ] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         DWA:  $dwa_status"

ldc_status=$([ $result5 -eq 0 ] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         LDC:  $ldc_status"

ive_status=$([ $result6 -eq 0 ] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         IVE:  $ive_status"

tde_status=$([ $result7 -eq 0 ] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         TDE:  $tde_status"

venc_status=$([ $result8 -eq 0 ] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         VENC: $venc_status"

vdec_status=$([ $result9 -eq 0 ] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         VDEC: $vdec_status"

jpu_status=$([ $result10 -eq 0 ] && \
    echo -e '\033[32mpass\033[0m' || echo -e '\033[31mfail\033[0m')
echo "         JPEG: $jpu_status"

{
    echo "========================================"
    echo "Multimedia hardware self-test result:"
    echo "TPU:  $([ $result1 -eq 0 ] && echo "pass" || echo "fail")"
    echo "VPSS: $([ $result2 -eq 0 ] && echo "pass" || echo "fail")"
    echo "DPU:  $([ $result3 -eq 0 ] && echo "pass" || echo "fail")"
    echo "DWA:  $([ $result4 -eq 0 ] && echo "pass" || echo "fail")"
    echo "LDC:  $([ $result5 -eq 0 ] && echo "pass" || echo "fail")"
    echo "IVE:  $([ $result6 -eq 0 ] && echo "pass" || echo "fail")"
    echo "TDE:  $([ $result7 -eq 0 ] && echo "pass" || echo "fail")"
    echo "VENC: $([ $result8 -eq 0 ] && echo "pass" || echo "fail")"
    echo "VDEC: $([ $result9 -eq 0 ] && echo "pass" || echo "fail")"
    echo "JPEG: $([ $result10 -eq 0 ] && echo "pass" || echo "fail")"
    echo "========================================"
    echo "Test Summary:"
    echo "TPU  (test_cv_warp_affine): $([ $result1 -eq 0 ] && echo "PASS" || echo "FAIL")"
    echo "VPSS  (test_vpss_convert_to): $([ $result2 -eq 0 ] && echo "PASS" || echo "FAIL")"
    echo "DPU  (test_dpu_fgs_thread): $([ $result3 -eq 0 ] && echo "PASS" || echo "FAIL")"
    echo "DWA  (test_dwa_rot_thread): $([ $result4 -eq 0 ] && echo "PASS" || echo "FAIL")"
    echo "LDC  (test_ldc_rot_thread): $([ $result5 -eq 0 ] && echo "PASS" || echo "FAIL")"
    echo "IVE  (test_ive_hist_thread): $([ $result6 -eq 0 ] && echo "PASS" || echo "FAIL")"
    echo "TDE  (test_tde_thread): $([ $result7 -eq 0 ] && echo "PASS" || echo "FAIL")"
    echo "VENC (bmvpuenc): $([ $result8 -eq 0 ] && echo "PASS" || echo "FAIL")"
    echo "VDEC (bm_test): $([ $result9 -eq 0 ] && echo "PASS" || echo "FAIL")"
    echo "JPEG (jpumulti): $([ $result10 -eq 0 ] && echo "PASS" || echo "FAIL")"

    if [ $result1 -eq 0 ] && [ $result2 -eq 0 ] && \
       [ $result3 -eq 0 ] && [ $result4 -eq 0 ] && \
       [ $result5 -eq 0 ] && [ $result6 -eq 0 ] && \
       [ $result7 -eq 0 ] && [ $result8 -eq 0 ] && \
       [ $result9 -eq 0 ] && [ $result10 -eq 0 ]; then
        echo "Overall Result: PASS"
    else
        echo "Overall Result: FAIL"
    fi

    echo "========================================"
    echo "Multimedia hardware self-test completed at: $(date)"
    echo "========================================"
} >> "$LOG_FILE"

# Clean up generated files
rm -rf csc_scale.csv* rgb24.bin_thread*

if [ $result1 -ne 0 ] || \
   [ $result2 -ne 0 ] || \
   [ $result3 -ne 0 ] || \
   [ $result4 -ne 0 ] || \
   [ $result5 -ne 0 ] || \
   [ $result6 -ne 0 ] || \
   [ $result7 -ne 0 ] || \
   [ $result8 -ne 0 ] || \
   [ $result9 -ne 0 ] || \
   [ $result10 -ne 0 ]; then
    exit 1
fi

# Create a tag file after execution is complete
touch "$FLAG_FILE"

exit 0
