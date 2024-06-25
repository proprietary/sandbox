(defun prime-number-p (n)
 "Common Lisp function to efficiently determine if a number is prime"
 (declare (optimize speed))
 (cond
  ((or (< n 2) (and (> n 2) (evenp n))) nil) ; 0, 1, and even numbers are not prime
  (t (loop for i from 3 upto (isqrt n) by 2
      when (= (mod n i) 0) do (return nil))
   t)))
