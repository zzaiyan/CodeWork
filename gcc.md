## 当前环境
```
系统：CentOS 7.9 x86_64
gcc版本：gcc version 4.8.5 20150623 (Red Hat 4.8.5-44) (GCC)
make版本：GNU Make 4.3
```

## 更新方法

### 1. 下载最新的源码包并解压缩 `gcc-12.2.0.tar.gz`

可在该地址寻找自己需要的版本 `http://ftp.gnu.org/gnu/gcc/`

  ```
  wget http://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.gz
  # 腾讯软件源 https://mirrors.cloud.tencent.com/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.gz
  tar -zxvf gcc-12.2.0.tar.gz
  ```

## 2.下载依赖及配置文件

```
yum -y install bzip2 #已安装可以跳过这一步
# 中标麒麟系统需要以下依赖
# yum -y install gmp mpfr mpc isl bzip2
cd gcc-12.2.0
./contrib/download_prerequisites
```

### 4. 配置
```
mkdir build
cd build/
../configure -enable-checking=release -enable-languages=c,c++ -disable-multilib

#–enable-languages表示你要让你的gcc支持那些语言，
#–disable-multilib不生成编译为其他平台可执行代码的交叉编译器。
#–disable-checking生成的编译器在编译过程中不做额外检查，
#也可以使用*–enable-checking=xxx*来增加一些检查
```

### 5. 编译
```
make -j2
```
#这一步需要时间非常久 可以使用 make -j4 让make最多运行四个编译命令同时运行，加快编译速度（建议不要超过CPU核心数量的2倍）

### 6. 安装
```
make install
```
### 7. 验证gcc版本
```
gcc -v
```

```
Using built-in specs.
COLLECT_GCC=/usr/local/bin/gcc
COLLECT_LTO_WRAPPER=/usr/local/libexec/gcc/x86_64-pc-linux-gnu/12.2.0/lto-wrapper
Target: x86_64-pc-linux-gnu
Configured with: ../configure -enable-checking=release -enable-languages=c,c++ -disable-multilib
Thread model: posix
Supported LTO compression algorithms: zlib
gcc version 12.2.0 (GCC)
```

验证：gcc -v；或者g++ -v，如果显示的gcc版本仍是以前的版本，就需要重启系统；

或者可以查看gcc的安装位置：`which gcc`；
然后在查看版本 `/usr/local/bin/gcc -v`
确定以及配置成功后可以将原先的版本删除.

### 1. 删除旧版本
```
yum -y remove gcc g++
```

### 2. 配置新版本全局可用
```
ln -s /usr/local/bin/gcc /usr/bin/gcc
```

### 3. 更新动态库
```
#查看当前的动态库
strings /usr/lib64/libstdc++.so.6 | grep CXXABI
rm -f /usr/lib64/libstdc++.so.6
ln -s /usr/local/lib64/libstdc++.so.6.0.29 /usr/lib64/libstdc++.so.6
#查看更新后的动态库
strings /usr/lib64/libstdc++.so.6 | grep CXXABI
# 安装后的动态库会位于/usr/local/lib64目录下，
#其他版本在该目录下寻找对应的动态库libstdc++.so.6.X.XX
```