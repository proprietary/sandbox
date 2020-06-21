public class Solution {
	public String convertToBase7(int num) {
		if (num == 0) {
			return "0";
		}
		final var sb = new StringBuilder();
		final var isNegative = num < 0;
		num = Math.abs(num);
		while (num > 0) {
			sb.append(num % 7);
			num /= 7;
		}
		if (isNegative) {
			sb.append('-');
		}
		return sb.reverse().toString();
	}

	public static void main(String[] args) {
		assert "202".equals(new Solution().convertToBase7(100));
		assert "-10".equals(new Solution().convertToBase7(-7));
	}
}
