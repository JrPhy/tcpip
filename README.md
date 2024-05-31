mkdir build && cd build
cmake ../
make\
./server_thread ip:port\
in another terminal ./client_thread ip:port

## 1. 流程
| server |  | client | 
| :---: | :---: | :---: | 
| socekt() |  | socekt()  | 
| bind() |  |  | 
| 以上為建立socekt() |  | 以上為建立socekt() |
| listen() | <--要求連線(第一次握手) | connect()  | 
| 阻塞至連上  |  |  | 
| accept() | 同意連線(第二次握手)--> | connect()  | 
| recv() | <--發送訊息(第三次握手) | send() |
| close() | | close() |

TCP 建立連線時會有三次握手
1. client 發送 connect 給 server (listening)
2. server 接收到後 accept 再傳給 client (connect)
3. client 接收到後開始與 server 通信
斷開連線有四次揮手。

## 2. Socket
第一步要先建立 socket，linux 中使用```int socket(int domain, int type, int protocol);```來建立。成功產生socket時，會返回該 socket 的檔案描述符 (socket file descriptor)，我們可以透過它來操作 socket。失敗則會回傳-1(INVALID_SOCKET)。

#### 1. domain
AF_UNIX/AF_LOCAL：讓兩個程式共享一個檔案系統(file system)
AF_INET , AF_INET6 ：讓兩台主機透過網路進行資料傳輸，AF_INET使用的是IPv4協定，而AF_INET6則是IPv6協定。

#### 2. type
SOCK_STREAM：TCP protocol，提供一個序列化的連接導向位元流，可以做位元流傳輸。
SOCK_DGRAM：UDP protocol提供的是一個一個的資料包(datagram)。

#### 3. protocol
設定 socket 的協定標準，0 是讓 kernel 選擇 type 對應的默認協議。

## 3. bind
再來要指定 ip(字串) 與 port(整數)，```iner_addr(ip string)```將 ipv4 的字串轉為整數，```htons(port)```將本機端的字節序(endian)轉換成了網路端的字節序，最後傳入下方來綁定 ip:port。
```int bind(int sockfd, struct sockaddr* addr, int addrlen);```

## 4. listen
socket 綁定成功後就可以使用 ```int listen(int sockfd, int backlog);```監聽，backlog 表示最多能有幾個人能連入 server。成功為 0，產生錯誤則回傳 -1。此函數就是在監聽，看是否有 client 發送握手訊，即第一次握手。

## 5. accept
接著進入無窮迴圈中等待連線進入，當有新的連線進入後使用 ```int accept(int sockfd, struct sockaddr addr, socklen_t addrlen);```來接收新的連線。將前面所建立的 socket 傳入，並將結構體和結構體大小傳入，就可以開始與 client 端收發訊息。及第二次握手。

## 6. connect
就是 client 端的 bind，要綁對方的 ip:port。```int connect(int sockfd, struct sockaddr *server, int addr_len);```。client 端藉由 connect 發送握手訊息給 server。
