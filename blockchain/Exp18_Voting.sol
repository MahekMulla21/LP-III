// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

// Exp 18: E-Voting dApp - smart contract
contract Voting {
    struct Candidate {
        uint256 id;
        string name;
        uint256 voteCount;
    }

    address public admin;
    bool public votingOpen;
    Candidate[] public candidates;
    mapping(address => bool) public hasVoted;

    event Voted(address indexed voter, uint256 candidateId);

    modifier onlyAdmin() {
        require(msg.sender == admin, "Only admin allowed");
        _;
    }

    constructor() {
        admin = msg.sender;
        votingOpen = true;
    }

    function addCandidate(string memory _name) public onlyAdmin {
        candidates.push(Candidate(candidates.length, _name, 0));
    }

    function vote(uint256 _candidateId) public {
        require(votingOpen, "Voting is closed");
        require(!hasVoted[msg.sender], "You have already voted");
        require(_candidateId < candidates.length, "Invalid candidate");
        hasVoted[msg.sender] = true;
        candidates[_candidateId].voteCount += 1;
        emit Voted(msg.sender, _candidateId);
    }

    function closeVoting() public onlyAdmin {
        votingOpen = false;
    }

    function getCandidateCount() public view returns (uint256) {
        return candidates.length;
    }

    function getWinner() public view returns (string memory name, uint256 votes) {
        require(candidates.length > 0, "No candidates");
        uint256 win = 0;
        for (uint256 i = 1; i < candidates.length; i++) {
            if (candidates[i].voteCount > candidates[win].voteCount) win = i;
        }
        return (candidates[win].name, candidates[win].voteCount);
    }
}
