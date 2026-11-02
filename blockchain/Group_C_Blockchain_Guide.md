# LP-III Group C (Exp 13-18): What to perform in the practical

Tools: Chrome/Firefox + MetaMask extension, Remix IDE (https://remix.ethereum.org), Sepolia test network.
Never use real money. Never share your seed phrase.

---
## Exp 13: Installation of MetaMask and study spending of Ether per transaction

**Steps to perform**
1. Add the MetaMask extension from https://metamask.io/download (Chrome/Firefox/Brave).
2. Click Create a new wallet, set a password, write down the 12-word Secret Recovery Phrase, confirm it.
3. Turn on "Show test networks" (Settings > Advanced) and switch the network to Sepolia.
4. Get free test ETH from a Sepolia faucet (e.g. Google Cloud Web3 faucet, Alchemy, Infura) by pasting your account address.
5. Create a second account (Account 2) and Send e.g. 0.01 ETH from Account 1 to Account 2.
6. Open the Activity tab > the transaction > View on Etherscan, and note the values below.

**What to observe / write in journal**
| Item | Value (example) |
|---|---|
| Amount sent | 0.01 ETH |
| Gas limit (standard ETH transfer) | 21,000 units |
| Gas price = Base fee + Priority fee | e.g. 1.5 Gwei |
| Transaction fee | Gas used x Gas price = 21,000 x 1.5 Gwei = 0.0000315 ETH |
| Total spent | Amount + Fee |

Formula: **Transaction fee = Gas used x (Base fee + Priority fee)**, 1 ETH = 10^9 Gwei = 10^18 wei.
Repeat with a different gas option (Low / Market / Aggressive) and compare the fee.

---
## Exp 14: Create your own wallet using MetaMask for crypto transactions

**Steps to perform**
1. Open MetaMask > Create wallet (as in Exp 13). Record: wallet/account address (0x...), network.
2. Add Account 2 (profile icon > Add account).
3. Fund Account 1 from the faucet; Send 0.005 ETH to Account 2 (paste its address, confirm).
4. Check balances of both accounts and the transaction hash on https://sepolia.etherscan.io.
5. Receive: copy Account 1 address and ask a friend to send test ETH.

**What to observe:** account address, balance before/after, transaction hash, status (Confirmed), block number, fee.

---
## Exp 15: Smart contract for a bank account (Deposit, Withdraw, Show balance)

Code: `Exp15_BankAccount.sol` (compiled OK with solc 0.8.26).

**Steps in Remix**
1. Create file BankAccount.sol, paste the code.
2. Solidity Compiler tab > compiler 0.8.x > Compile.
3. Deploy & Run tab > Environment: **Injected Provider - MetaMask** (Sepolia) [or Remix VM for quick test] > Deploy > confirm in MetaMask.
4. Set VALUE = 1 and unit Ether > click `deposit` > confirm.
5. Click `showBalance` -> output `1000000000000000000` (wei = 1 ETH).
6. In `withdraw` enter `500000000000000000` > transact; click `showBalance` -> `500000000000000000`.
7. Note gas used / transaction cost from the Remix console for deploy, deposit, withdraw.

**Expected output**
| Action | Result |
|---|---|
| deposit 1 ETH | balance = 1000000000000000000 |
| withdraw 0.5 ETH | balance = 500000000000000000 |
| withdraw 5 ETH | reverts: "Insufficient balance" |

---
## Exp 16: Solidity - Student data with Structure, Array, Fallback; observe fee and gas

Code: `Exp16_StudentData.sol` (compiled OK).

**Steps in Remix**
1. Compile and deploy as above (Injected Provider - MetaMask, Sepolia).
2. `addStudent(1, "Rahul", "BE Computer", 85)` then `addStudent(2, "Sneha", "BE Computer", 90)`.
3. `getTotalStudents` -> 2; `getStudent(0)` -> 1, Rahul, BE Computer, 85; `students(1)` -> 2, Sneha, ...
4. Fallback: in the Low-level interactions box at the bottom, type any calldata e.g. `0x1234`, click Transact -> the fallback runs and emits `FallbackCalled`.
5. For each transaction open the Remix console (or Etherscan) and note: **gas used, gas price, transaction fee** (fee = gas used x gas price).

**Observation table (fill with your values)**
| Transaction | Gas used | Gas price | Fee |
|---|---|---|---|
| Deploy | ~ | | |
| addStudent | ~ | | |
| Fallback call | ~ | | |

---
## Exp 17: Survey report - types of blockchains and real-time use cases

Write this as a report (Introduction, 4 types, comparison, use cases, conclusion).

| Type | Who can join | Speed | Examples | Real-time use cases |
|---|---|---|---|---|
| Public | Anyone (permissionless) | Slow | Bitcoin, Ethereum | Cryptocurrency, DeFi, NFTs, smart contracts |
| Private | Selected/authorized users in one organization | Fast | Hyperledger Fabric, Corda | Internal auditing, asset management, internal voting |
| Hybrid | Mix of public and private, access via smart contracts | Medium | Ripple (XRP), IBM Food Trust | Healthcare records, real estate, government, finance |
| Consortium | Group of organizations (federated) | Fast | Hyperledger, Tendermint, Multichain | Banking, supply chain / food tracking, payment processors |

Add for each type: 3 advantages and 3 disadvantages (Public: trustable, secure, decentralized / slow, high energy use, hard to regulate. Private: fast, scalable, private / more centralized, less secure, trust issues. Hybrid: customizable, cheap, secure / hard to maintain, less transparent, no incentives. Consortium: fast, shared authority, private / less flexible, can be corrupted, vulnerable if nodes are compromised).
Real-time examples to mention: supply chain (Walmart food traceability), cross-border payments (Ripple), land records, healthcare data sharing, e-voting.

---
## Exp 18 (Mini project): Blockchain-based dApp for an e-voting system

Files: `Exp18_Voting.sol` (contract, compiled OK) and `Exp18_index.html` (front end using ethers.js + MetaMask).

**Steps**
1. Remix: compile and deploy `Voting` (Injected Provider - MetaMask, Sepolia). Copy the deployed contract address.
2. In Remix call `addCandidate("Alice")`, `addCandidate("Bob")`, `addCandidate("Carol")` from the admin account.
3. Open `Exp18_index.html`, replace `PASTE_DEPLOYED_CONTRACT_ADDRESS` with the address. Serve it with `python -m http.server 8000` and open http://localhost:8000/Exp18_index.html (MetaMask does not inject on file:// pages in some browsers).
4. Click Connect MetaMask > the candidates and Vote buttons appear.
5. Vote from Account 1; voting again from the same account fails with "You have already voted". Switch MetaMask to Account 2 and vote for another candidate.
6. Click Show winner; admin can Close voting.

**Features to mention in viva:** one vote per address (mapping), only admin adds candidates (modifier), votes stored on-chain and transparent/immutable, events logged, front end connects through MetaMask.
