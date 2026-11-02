// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

// Exp 16: Student data using Structure, Array and Fallback function
contract StudentData {
    // Structure
    struct Student {
        uint256 rollNo;
        string name;
        string course;
        uint256 marks;
    }

    // Dynamic array of structures
    Student[] public students;

    event FallbackCalled(address sender, uint256 value, bytes data);

    function addStudent(uint256 _rollNo, string memory _name, string memory _course, uint256 _marks) public {
        students.push(Student(_rollNo, _name, _course, _marks));
    }

    function getStudent(uint256 index) public view returns (uint256, string memory, string memory, uint256) {
        require(index < students.length, "Invalid index");
        Student memory s = students[index];
        return (s.rollNo, s.name, s.course, s.marks);
    }

    function getTotalStudents() public view returns (uint256) {
        return students.length;
    }

    // Fallback: runs when a function that does not exist is called (or data is sent)
    fallback() external payable {
        emit FallbackCalled(msg.sender, msg.value, msg.data);
    }

    // Receive: runs when plain Ether is sent with no data
    receive() external payable {
        emit FallbackCalled(msg.sender, msg.value, "");
    }
}
