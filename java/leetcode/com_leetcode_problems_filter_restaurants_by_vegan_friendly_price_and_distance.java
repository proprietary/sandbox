import java.util.*;
import java.util.stream.*;

public class Solution {
	enum RestaurantFeature {
		ID (0),
		RATING (1),
		VEGAN_FRIENDLY (2),
		PRICE (3),
		DISTANCE (4);

		private final int value;
		private RestaurantFeature(final int value) {
			this.value = value;
		}

		public int getValue() {
			return value;
		}
	}

	class Restaurant {
		private int[] restaurantFeatures;
		
		public Restaurant(int[] restaurantFeatures) {
			this.restaurantFeatures = restaurantFeatures;
		}
		
		private int getFeature(RestaurantFeature feature) {
			return restaurantFeatures[feature.getValue()];
		}

		public int getId() {
			return getFeature(RestaurantFeature.ID);
		}

		public int getRating() {
			return getFeature(RestaurantFeature.RATING);
		}

		public int getVeganFriendly() {
			return getFeature(RestaurantFeature.VEGAN_FRIENDLY);
		}

		public int getPrice() {
			return getFeature(RestaurantFeature.PRICE);
		}

		public int getDistance() {
			return getFeature(RestaurantFeature.DISTANCE);
		}
	}
	
    public List<Integer> filterRestaurants(int[][] restaurants, int veganFriendly, int maxPrice, int maxDistance) {
		var o = new ArrayList<Restaurant>();
        for (int i = 0; i < restaurants.length; ++i) {
			final var r = new Restaurant(restaurants[i]);
			if ((veganFriendly == 1 && r.getVeganFriendly() == 0) || r.getPrice() > maxPrice || r.getDistance() > maxDistance) {
				continue;
			}
			o.add(r);
		}
		o.sort((a, b) -> {
				var c = b.getRating() - a.getRating();
				if (c == 0) {
					return b.getId() - a.getId();
				}
				return c;
			});
		return o.stream().map(r -> r.getId()).collect(Collectors.toList());
    }

	public static void main(String[] args) {
		TestCase(new int[]{3,1,5}, new int[][]{{1,4,1,40,10}, {2,8,0,50,5}, {3,8,1,30,4}, {4,10,0,10,3}, {5,1,1,15,1}}, 1, 50, 10);
		TestCase(new int[]{4,3,2,1,5}, new int[][]{{1,4,1,40,10},{2,8,0,50,5},{3,8,1,30,4},{4,10,0,10,3},{5,1,1,15,1}}, 0, 50, 10);
	}

	private static void TestCase(int expected[], int[][] restaurants, int veganFriendly, int maxPrice, int maxDistance) {
		var r = new Solution().filterRestaurants(restaurants, veganFriendly, maxPrice, maxDistance);
		for (var i = 0; i < r.size(); ++i) {
			assert r.get(i) == expected[i];
		}
	}
}
