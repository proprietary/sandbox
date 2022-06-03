'use strict';

function baseConversion(n, targetRadix, targetRadixDigits) {
    if (targetRadixDigits.length !== targetRadix) { throw new Error(); }
    let o = [];
    while (n > 0) {
        let t = n % targetRadix;
        n = Math.floor(n / targetRadix);
        o.push(targetRadixDigits[t]);
    }
    return o.reverse().join('');
}

// examples:
baseConversion(20, 16, ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']) // '14'
baseConversion(0x14, 10, (() => { let acc = []; for (let i = 0; i < 10; ++i) { acc.push(i.toString()); }; return acc; })()) // '20'
baseConversion(25, 26, (() => { let acc = []; for (let i = 'a'.charCodeAt(); i <= 'z'.charCodeAt(); ++i) { acc.push(String.fromCharCode(i)); }; return acc; })()) // 'z'
baseConversion(9999999999999999999999999, 26, (() => { let acc = []; for (let i = 'a'.charCodeAt(); i <= 'z'.charCodeAt(); ++i) { acc.push(String.fromCharCode(i)); }; return acc; })()) // 'ivicumdpbuauomcmom'

