FROM envoyproxy/envoy-build-ubuntu:41c5a05d708972d703661b702a63ef5060125c33

ENV DEBIAN_FRONTEND noninteractive

# install dependencies
RUN apt-get update && apt-get install -y libssl-dev libcurl4-openssl-dev cmake rustc cargo vim wget gnupg
RUN wget https://download.01.org/intel-sgx/latest/linux-latest/distro/ubuntu20.04-server/sgx_linux_x64_sdk_2.23.100.2.bin
RUN chmod +x sgx_linux_x64_sdk_2.23.100.2.bin
RUN echo -e 'no\n/opt/intel\n' | ./sgx_linux_x64_sdk_2.23.100.2.bin 
#RUN source /opt/intel/sgxsdk/environment
RUN rm sgx_linux_x64_sdk_2.23.100.2.bin
RUN echo "deb [arch=amd64] https://download.01.org/intel-sgx/sgx_repo/ubuntu focal main" | tee /etc/apt/sources.list.d/intel-sgx.list
RUN wget -qO - https://download.01.org/intel-sgx/sgx_repo/ubuntu/intel-sgx-deb.key | apt-key add -
RUN echo "deb http://cz.archive.ubuntu.com/ubuntu bionic main" >>  /etc/apt/sources.list
RUN apt-get update -y && apt-get install -y libprotobuf10 libsgx-dcap-quote-verify libsgx-dcap-quote-verify-dev libsgx-dcap-ql-dev libsgx-uae-service libsgx-dcap-default-qpl libtdx-attest-dev

# config pccs
RUN rm /etc/sgx_default_qcnl.conf
COPY ./HANG/TDX/PCCS_config/sgx_default_qcnl.conf /etc/sgx_default_qcnl.conf

# create newuser
RUN useradd -m -s /bin/bash newuser && echo 'newuser:123456' | chpasswd && usermod -aG sudo newuser 

# copy tng into docker
WORKDIR /home/newuser
RUN mkdir team-half-burnt 
WORKDIR /home/newuser/team-half-burnt 
COPY . /home/newuser/team-half-burnt 

# install librats
RUN rm -rf /home/newuser/team-half-burnt/librats/build  
WORKDIR /home/newuser/team-half-burnt/librats
RUN cmake -DRATS_BUILD_MODE="tdx" -DBUILD_SAMPLES=on -H. -Bbuild
RUN make -C build all && make -C build install

# install envoy
RUN chown -R newuser:newuser /home/newuser
USER newuser
WORKDIR /home/newuser/team-half-burnt 
RUN bazel/setup_clang.sh /opt/llvm/
RUN echo "build --config=clang" >> user.bazelrc
RUN git config --global --add safe.directory /home/newuser/team-half-burnt 
RUN bazel build -c opt envoy