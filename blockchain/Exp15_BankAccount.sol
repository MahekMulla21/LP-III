// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

// Exp 15: Bank account smart contract - Deposit, Withdraw, Show balance
contract BankAccount {
    address public owner;
    mapping(address => uint256) private balances;

    event Deposited(address indexed customer, uint256 amount);
    event Withdrawn(address indexed customer, uint256 amount);

    constructor() {
        owner = msg.sender;
    }

    // Deposit money (enter the amount in the VALUE box of Remix, e.g. 1 Ether)
    function deposit() public payable {
        require(msg.value > 0, "Deposit amount must be greater than 0");
        balances[msg.sender] += msg.value;
        emit Deposited(msg.sender, msg.value);
    }

    // Withdraw money (amount in wei)
    function withdraw(uint256 amount) public {
        require(amount > 0, "Amount must be greater than 0");
        require(balances[msg.sender] >= amount, "Insufficient balance");
        balances[msg.sender] -= amount;
        (bool sent, ) = payable(msg.sender).call{value: amount}("");
        require(sent, "Transfer failed");
        emit Withdrawn(msg.sender, amount);
    }

    // Show balance of the caller (in wei)
    function showBalance() public view returns (uint256) {
        return balances[msg.sender];
    }
}
